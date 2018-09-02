open Common;
open Forms;

type model = {
  first: string,
  second: string,
  response: string,
  loading: bool,
  submited: bool,
};

type action =
  | FirstInputChange(string)
  | SecondInputChange(string)
  | Submit
  | LoadResponse(string);

let send = dispatch =>
  Js.Promise.(
    Fetch.fetch("/api/example/2")
    |> then_(Fetch.Response.text)
    |> then_(text => LoadResponse(text) |> dispatch |> resolve)
  )
  |> ignore;

let update = (model, action: action): (model, Command.command('action)) =>
  switch (action) {
  | FirstInputChange(value) => ({...model, first: value}, Command.null)
  | SecondInputChange(value) => ({...model, second: value}, Command.null)
  | Submit => ({...model, submited: true, loading: true}, Command.run(send))
  | LoadResponse(response) => (
      {...model, loading: false, response},
      Command.null,
    )
  };

Rembrandt.run(
  ~model={
    first: "first",
    second: "second",
    response: "",
    submited: false,
    loading: false,
  },
  ~middleWare=Rembrandt.MiddleWares.logger,
  ~update,
  ~view=
    ({first, second, loading, response}, dispatch) =>
      <form
        onSubmit={({ preventDefault }) => {
          preventDefault(());
          Submit |> dispatch;
        }}
        action=""
      >
        <span key="1">{text(first)}</span>
        <span key="2"> {text(second)}</span>
        <span key="3"> {text(response)}</span>
        <div key="5">
          <input
            key="99"
            value=first
            onInput={e => getValue(e)->FirstInputChange->dispatch}
          />
          <input
            key="698"
            value=second
            onInput={e => getValue(e)->SecondInputChange->dispatch}
          />
        </div>
        <button key="7"> {text("send")} </button>
      </form>,
  (),
);