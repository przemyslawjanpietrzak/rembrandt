open ElementsTypes;
open Div;
open Command;

type update('model, 'action) =
  ('model, 'action) => ('model, Command.command('action));

type view('model, 'action) = ('model, 'action => bool) => node;
type subscription('model, 'action) = ('model, 'action => bool) => unit;

let runCommand = (command, dispatchAction) =>
  (
    switch (command.commandType, command.commandAction, command.callback) {
    | (CAction, Some(commandAction), _) =>
      Js.Promise.make((~resolve, ~reject) =>
        dispatchAction(commandAction) |> ignore
      )
    | (Run, _, Some(callback)) =>
      Js.Promise.make((~resolve, ~reject) =>
        callback(dispatchAction) |> ignore
      )
    | (_, _, _) => Js.Promise.resolve()
    }
  )
  |> ignore;

let dispatch = (action, model, update) => update(model, action);
let run =
    (
      ~view: ('model, 'dispatch) => node,
      ~model: 'model,
      ~update: ('model, 'action) => ('model, Command.command('action)),
      ~initAction=Command.null,
      ~rootId="app",
      ~middlewares: list(('model, 'model, 'action) => unit)=[],
      ~subscription: ('model, 'dispatch) => unit = (mode, dispatch) => (),
      (),
    ) => {
  let root = ref(Dom.createElement("div"));
  let currentView = ref(<div />);
  let dispatchAction = ref(_ => ());
  let currentModel = ref(model);

  let dispatch = (~action, ~update) => {
    let (updatedModel, command) = update(currentModel^, action);
    middlewares
    |> List.iter(middleware =>
         middleware(currentModel^, updatedModel, action)
       );
    currentModel := updatedModel;
    let updatedView = view(currentModel^, dispatchAction^);
    let diff =
      VirtualDom.getDiff(~oldNode=currentView^, ~newNode=Some(updatedView));
    VirtualDom.patch(root^, diff);
    currentView := updatedView;
    runCommand(command, dispatchAction^);
  };

  dispatchAction := (action => dispatch(~action, ~update));
  runCommand(initAction, dispatchAction^);

  currentView := view(model, dispatchAction^);
  root := Render.render(currentView^) |> Dom.init(rootId);
  subscription(currentModel^, dispatchAction^);
};
