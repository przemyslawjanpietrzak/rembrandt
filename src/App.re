open Common

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
  ~view=(model, dispatch) => <div>
    <div style="height:100px;width:100px;" onClick={(a: string) => ADD(3) |> dispatch }>
      { string_of_int(model) |> text }
    </div>
  </div>
);
