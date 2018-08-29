open Common

type model = int;
type action =
  | ADD
  | SUB;

let update = (model: model, action: action): (model, Command.command('action)) => {
  switch action {
  | ADD => (model + 1, Command.null())
  | SUB => (model - 1, Command.null())
  };
};

Rembrandt.run(
  ~model=42,
  ~update=update,
  ~view=(model, dispatch) => <div>
    <div key="0" id="count">
      { string_of_int(model) |> text }
    </div>
    <button key="2" id="plus" onClick={(a: string) => ADD |> dispatch }>{ text("+") }</button>
    <button key="3" id="minus" onClick={(a: string) => SUB |> dispatch }>{ text("-") }</button>
  </div>
);
