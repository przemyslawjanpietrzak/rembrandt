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
let run = (
  ~view: ('model, 'dispatch) => node,
  ~model: 'model,
  ~update: ('model, 'action) => ('model, Command.command('action))
) => {
  let root = ref(Dom.createElement("div"));
  let currentView = ref(<div />);
  let dispatchAction = ref(_ => false);
  let currentModel = ref(model);

  let rec dispatch = (~action, ~update) => {
    let (updatedModel, command) = update(currentModel^, action);
    currentModel := updatedModel;
    let updatedView = view(currentModel^, dispatchAction^);
    VirtualDom.setPositions(~node=updatedView, ~initialPosition=0) |> ignore;
    let diff =
      VirtualDom.getDiff(~oldNode=currentView^, ~newNode=Some(updatedView));
    VirtualDom.patch(root^, diff);

    /* TODO: async */
    switch (command.commandType, command.commandAction) {
      | (CAction, Some(commandAction)) => {
        Js.Promise.make((~resolve, ~reject) => {
          /* dispatch(
            ~update=update,
            ~action=(command.commandAction, Command.null()),
          ) |> ignore; */
          dispatchAction^(commandAction) |> ignore;
        }) |> ignore;
      }
      /* | Run => 43 |> ignore;
      | Null => 44 |> ignore; */
    };

    true;
  };

  dispatchAction := action => dispatch(~action=action, ~update=update);

  currentView := view(model, dispatchAction^);
  root := render(currentView^) |> Dom.init("app");
};