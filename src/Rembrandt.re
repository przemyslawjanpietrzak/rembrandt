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

let dispatch = (action, model, update) => update(model, action);
let run =
    (
      ~view: ('model, 'dispatch) => node,
      ~model: 'model,
      ~update: ('model, 'action) => ('model, Command.command('action)),
    ) => {
  let root = ref(Dom.createElement("div"));
  let currentView = ref(<div />);
  let dispatchAction = ref(_ => 42 |> ignore);
  let currentModel = ref(model);

  let rec dispatch = (~action, ~update) => {
    let (updatedModel, command) = update(currentModel^, action);
    currentModel := updatedModel;
    let updatedView = view(currentModel^, dispatchAction^);
    VirtualDom.setPositions(~node=updatedView, ~initialPosition=0) |> ignore;
    let diff =
      VirtualDom.getDiff(~oldNode=currentView^, ~newNode=Some(updatedView));
    VirtualDom.patch(root^, diff);

    (
      switch (command.commandType, command.commandAction, command.callback) {
      | (CAction, Some(commandAction), _) =>
        Js.Promise.make((~resolve, ~reject) =>
          dispatchAction^(commandAction) |> ignore
        )
      | (Run, _, Some(callback)) =>
        Js.Promise.make((~resolve, ~reject) =>
          callback(dispatchAction^) |> ignore
        )
      | (_, _, _) => Js.Promise.resolve()
      }
    )
    |> ignore;
  };

  dispatchAction := (action => dispatch(~action, ~update));

  currentView := view(model, dispatchAction^);
  root := render(currentView^) |> Dom.init("app");
};