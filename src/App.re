open Main

type model = int;
type action =
  | ADD(int)
  | SUB(int);

let update = (model: model, action: action): model => {
  switch action {
  | ADD(value) => model + value
  | SUB(value) => model - value
  };
};

Rembrandt.run(
  ~model=42,
  ~update=update,
  ~view=(model, dispatch) => <div>(text("42"))</div>
);
