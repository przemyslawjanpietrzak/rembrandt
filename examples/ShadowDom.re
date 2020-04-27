open Rembrandt.Elements;

type model = int;
type action =
  | Add
  | Sub;

let update =
    (model: model, action: action): (model, Command.command('action)) =>
  switch (action) {
  | Add => (model + 1, Command.null)
  | Sub => (model - 1, Command.null)
  };

Rembrandt.run(
  ~model=42,
  ~update,
  ~view=
    (model, dispatch) =>
      <div>
      <shadowRoot>
        <div id="count"> {string_of_int(model) |> text} </div>
        <button id="plus" onClick={_ => Add |> dispatch}>
          {"+" |> text}
        </button>
          <button id="minus" onClick={_ => Sub |> dispatch}>
          {"-" |> text}
          </button>
      </shadowRoot>
      </div>,
  (),
);