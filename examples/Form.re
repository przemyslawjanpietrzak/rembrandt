open Common;
open Forms;

type model = {
  first: string,
  second: string,
  submited: bool,
};
type action =
  | FirstInputChange(string)
  | SecondInputChange(string)

let update =
    (model: model, action: action): (model, Command.command('action)) =>
  switch (action) {
  | FirstInputChange(value) => ({ ...model, first: value }, Command.null)
  | SecondInputChange(value) => ({ ...model, second: value }, Command.null)
  };

Rembrandt.run(
  ~model={
    first: "first",
    second: "second",
    submited: false,
  },
  ~update,
  ~view=
    ({ first, second }, dispatch) =>
      <div>
        { text(first) }
        <input
          value=first
          onInput={e => getValue(e) -> FirstInputChange -> dispatch}
        />
        { text(second) }
        <input
          value=second
          onInput={e => getValue(e) -> SecondInputChange -> dispatch}
        />
      </div>,
  (),
);