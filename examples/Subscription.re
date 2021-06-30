open Rembrandt.Elements;

type model = int;
type action =
  | Add;

let update =
    (model: model, action: action): (model, Command.command('action)) =>
  switch (action) {
  | Add => (model + 1, Command.null)
  };

Rembrandt.run(
  ~model=42,
  ~update,
  ~subscription=
    (model, dispatch) => {
      Js.Global.setInterval(
        () => {
          Js.log(model);
          Add |> dispatch;
          ();
        },
        2500,
      )|>ignore;
      ();
    },
  ~view=
    (model, _dispatch) =>
      <div>
        <div id="count"> {string_of_int(model) |> text} </div>
        <div> {"Number should increase" |> text} </div>
      </div>,
  (),
);
