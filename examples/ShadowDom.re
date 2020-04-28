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
        <div id="count"> {string_of_int(model) |> text} </div>
      <shadowRoot mode=ShadowDomOpenMode>
        <button id="plus" onClick={_ => Add |> dispatch}>
          {"+" |> text}
        </button>
      </shadowRoot>
      <shadowRoot mode=ShadowDomOpenMode>
          <button id="minus" onClick={_ => Sub |> dispatch}>
          {"-" |> text}
          </button>
      </shadowRoot>
      <shadowRoot mode=ShadowDomOpenMode>
      <div>
       { "Some element in close shadow dom" |> text  }
      </div>
      </shadowRoot>
      </div>,
  (),
);