open Common;
open Command;

type update('model, 'action) =
  ('model, 'action) => ('model, Command.command('action));

type view('model, 'action) = ('model, 'action => bool) => node;

let runCommand = (command, dispatchAction) => {
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
    } |> ignore;
}

let dispatch = (action, model, update) => update(model, action);

let run =
    (
      ~view: ('model, 'dispatch) => node,
      ~model: 'model,
      ~update: ('model, 'action) => ('model, Command.command('action)),
      ~init=Command.null,
      ~rootId="app",
      ~middleWare:('model, 'model, 'action) => unit = (_, _, _) => (),
      (),
    ) => {
  let root = ref(Dom.createElement("div"));
  let currentView = ref(<div />);
  let dispatchAction = ref(_ => ());
  let currentModel = ref(model);

  let dispatch = (~action, ~update) => {
    let (updatedModel, command) = update(currentModel^, action);
    middleWare(currentModel^, updatedModel, action);
    currentModel := updatedModel;
    let updatedView = view(currentModel^, dispatchAction^);
    let diff = VirtualDom.getDiff(~oldNode=currentView^, ~newNode=Some(updatedView));
    VirtualDom.patch(root^, diff);
    currentView := updatedView;
    runCommand(command, dispatchAction^);
  };

  dispatchAction := (action => dispatch(~action, ~update));
  runCommand(init, dispatchAction^);

  currentView := view(model, dispatchAction^);
  root := Render.render(currentView^) |> Dom.init(rootId);
};