open Common;
open Command;

type update('model, 'action) =
  ('model, 'action) => ('model, Command.command('action));

type view('model, 'action) = ('model, 'action => bool) => node;

type run('model, 'action) = {
  view: ('model, 'action => 'model) => node,
  update: ('model, 'action) => 'model,
  model: 'model,
};

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
      ~middleWare:('model, 'model) => unit = (_, _) => (),
      (),
    ) => {
  let root = ref(Dom.createElement("div"));
  let currentView = ref(<div />);
  let dispatchAction = ref(_ => ());
  let currentModel = ref(model);

  let rec dispatch = (~action, ~update) => {
    let (updatedModel, command) = update(currentModel^, action);
    middleWare(currentModel^, updatedModel);
    currentModel := updatedModel;
    let updatedView = view(currentModel^, dispatchAction^);
    /* VirtualDom.setPositions(~node=updatedView, ~initialPosition=0) |> ignore; */
    let diff = VirtualDom.getDiff(~oldNode=currentView^, ~newNode=Some(updatedView));
    VirtualDom.patch(root^, diff);
    runCommand(command, dispatchAction^);
  };

  dispatchAction := (action => dispatch(~action, ~update));
  runCommand(init, dispatchAction^);

  currentView := view(model, dispatchAction^);
  root := render(currentView^) |> Dom.init(rootId);
};