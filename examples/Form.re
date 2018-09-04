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

let send = dispatch =>
  Js.Promise.(
    Fetch.fetchWithInit(
      "/api/form",
      Fetch.RequestInit.make(~method_=Post, ()),
    )
    |> then_(Fetch.Response.text)
    |> then_(text => LoadResponse(text) |> dispatch |> resolve)
  )
  |> ignore;

let update = (model, action: action): (model, Command.command('action)) =>
  switch (action) {
  | FirstInputChange(value) => ({...model, first: value}, Command.null)
  | SecondInputChange(value) => ({...model, second: value}, Command.null)
  | Submit => ({...model, loading: true, response: "in progress"}, Command.run(send))
  | LoadResponse(response) => (
      {...model, loading: false, response},
      Command.null,
    )
  };

Rembrandt.run(
  ~model={
    first: "",
    second: "",
    response: "example string #2",
    loading: false,
  },
  ~middleWare=Rembrandt.MiddleWares.logger,
  ~update,
  ~view=
    ({first, second, loading, response}, dispatch) =>
      <form onSubmit={_ => Submit |> dispatch} action="#">
        <div key="1" id="first"> {text("first: " ++ first)} </div>
        <div key="2" id="second"> {text("second: " ++ second)} </div>
        <div key="3" id="response"> {text( response)} </div>
        <div key="4" id="loading"> {text(loading ? "loading" : "loaded")} </div>
        <div key="5">
          <input
            key="1"
            id="first-input"
            value=first
            onInput={e => FirstInputChange(getValue(e)) |> dispatch}
          />
          <input
            key="2"
            id="second-input"
            value=second
            onInput={e => SecondInputChange(getValue(e)) |> dispatch}
          />
        </div>
        <button key="7"> {text("send")} </button>
      </form>,
  (),
);