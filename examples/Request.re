open Common;

type model = string;
type action =
  | FetchData
  | LoadData(string)
  | Error;

let request = dispatch =>
  Js.Promise.(
    Fetch.fetch("/api/example/1")
    |> then_(Fetch.Response.text)
    |> then_(text => LoadData(text) |> dispatch |> resolve)
  )
  |> ignore;

let update =
    (model: model, action: action): (model, Command.command('action)) =>
  switch (action) {
  | FetchData => ("loading", Command.run(request))
  | LoadData(text) => (text, Command.null)
  | Error => ("error", Command.null)
  };

Rembrandt.run(~model="begin", ~update, ~view=(model, dispatch) =>
  <div>
    <div key="0" id="data"> {model |> text} </div>
    <button key="2" id="request" onClick={_ => FetchData |> dispatch}>
      {text("Load Data")}
    </button>
  </div>
);