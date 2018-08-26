open Common

type model = int;
type action =
  | ADD
  | SUB;

let update = (model: model, action: action): model => {
  switch action {
  | ADD => model + 1
  | SUB => model - 1
  };
};

Rembrandt.run(
  ~model=42,
  ~update=update,
  ~view=(model, dispatch) => <div>
    <div key="0">
      { string_of_int(model) |> text }
    </div>
    <button key="2" onClick={(a: string) => ADD |> dispatch }>{ text("+") }</button>
    <button key="3" onClick={(a: string) => SUB |> dispatch }>{ text("-") }</button>
  </div>
);
