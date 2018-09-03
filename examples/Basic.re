open Rembrandt.Elements

type model = int;
type action =
  | Add
  | Sub
  | Twice

let update = (model: model, action: action): (model, Command.command('action)) => {
  switch action {
  | Add => (model + 1, Command.null)
  | Sub => (model - 1, Command.null)
  | Twice => (model + 1, Command.action(Add))
  };
};

Rembrandt.run(
  ~rootId="app",
  ~model=42,
  ~update=update,
  ~view=(model, dispatch) => <div>
    <div key="1" id="count">
      { string_of_int(model) |> text }
    </div>
    <button key="2" id="plus" onClick={ _ => Add |> dispatch }>{ text("+") }</button>
    <button key="3" id="minus" onClick={ _ => Sub |> dispatch }>{ text("-") }</button>
    <button key="4" id="minus" onClick={ _ => Twice |> dispatch }>{ text("twice +") }</button>
  </div>,
  (),
);
