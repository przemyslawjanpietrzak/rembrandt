open Common

type model = int;
type actionT =
  | ADD
  | SUB
  | ASYNC;

let update = (model: model, action: actionT): (model, Command.command('action)) => {
  switch action {
  | ADD => (model + 1, Command.null);
  | SUB => (model - 1, Command.null);
  | ASYNC => (model + 1, Command.action(ADD));
  };
};

Rembrandt.run(
  ~model=42,
  ~update=update,
  ~view=(model, dispatch) => <div>
    <div key="0" id="count">
      { string_of_int(model) |> text }
    </div>
    <button key="2" id="plus" onClick={ _ => ADD |> dispatch }>{ text("+") }</button>
    <button key="3" id="minus" onClick={ _ => SUB |> dispatch }>{ text("-") }</button>
    <button key="4" id="double" onClick={ _ => ASYNC |> dispatch }>{ text("double") }</button>
  </div>,
);
