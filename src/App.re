open Main

type model = int;
type action =
  | ADD(int)
  | SUB(int);

let update = (model: model, action: action) => {
  switch action {
  | ADD(value) => model + value
  | SUB(value) => model - value
  };
};

Rembrandt.run(
  ~model=42,
  ~update=update,
  ~view=(model, dispatch) => <div></div>
);
