open Rembrandt.Elements;
open Rembrandt.Forms;

type model = {
  first: string,
  second: string,
  response: string,
  loading: bool,
};

type action =
  | FirstInputChange(string)
  | SecondInputChange(string)
  | Submit
  | LoadResponse(string);

let send = (firstName, lastName, dispatch) => {
  let payload = Js.Dict.empty();
  Js.Dict.set(payload, "firstName", Js.Json.string(firstName));
  Js.Dict.set(payload, "lastName", Js.Json.string(lastName));
  Js.Promise.(
    Fetch.fetchWithInit(
      "/api/form",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=
          Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(payload))),
        ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
        (),
      ),
    )
    |> then_(Fetch.Response.text)
    |> then_(text => LoadResponse(text) |> dispatch |> resolve)
  )
  |> ignore;
};

Rembrandt.run(
  ~model={first: "", second: "", response: "", loading: false},
  ~update=
    (model, action: action) => (
      switch (action) {
      | FirstInputChange(value) => ({...model, first: value}, Command.null)
      | SecondInputChange(value) => (
          {...model, second: value},
          Command.null,
        )
      | Submit => (
          {...model, loading: true},
          Command.run(send(model.first, model.second)),
        )
      | LoadResponse(response) => (
          {...model, loading: false, response},
          Command.null,
        )
      }: (
        model,
        Command.command('action),
      )
    ),
  ~view=
    ({first, second, loading, response}, dispatch) =>
      <form onSubmit={_ => Submit |> dispatch} action="#">
        <div id="first"> {text("first: " ++ first)} </div>
        <div id="second"> {text("second: " ++ second)} </div>
        <div id="response"> {text("response: " ++ response)} </div>
        <div id="loading"> {text(loading ? "loading" : "loaded")} </div>
        <div>
          <input
            id="first-input"
            value=first
            onInput={e => FirstInputChange(getValue(e)) |> dispatch}
          />
          <input
            id="second-input"
            value=second
            onInput={e => SecondInputChange(getValue(e)) |> dispatch}
          />
        </div>
        <button> {text("send")} </button>
      </form>,
  ~middlewares=[Rembrandt.MiddleWares.logger],
  (),
);
