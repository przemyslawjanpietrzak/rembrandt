open Common;

type update('model, 'action) =
  ('model, 'action) => ('model, Command.command('action));

type appParams('model, 'action) = {
  view: ('model, 'action => 'model) => node,
  update: ('model, 'action) => 'model,
  model: 'model,
};

let dispatch = (action, model, update) => update(model, action);
let run = (~view, ~model: 'model, ~update) => {
  let root = ref(Dom.createElement("div"));
  let currentView = ref(<div />);
  let dispatchAction = ref(_ => false);
  let currentModel = ref(model);

  let dispatch = (action, update) => {
    let (updatedModel, _command) = update(currentModel^, action);
    currentModel := updatedModel;
    let updatedView = view(currentModel^, dispatchAction^);
    VirtualDom.setPositions(~node=updatedView, ~initialPosition=0) |> ignore;
    let diff =
      VirtualDom.getDiff(~oldNode=currentView^, ~newNode=Some(updatedView));
    VirtualDom.patch(root^, diff);

    /* TODO: async */
    /* switch command.commandType {
           | CAction => 42 |> ignore;
           | Run => 43 |> ignore;
           | Null => 44 |> ignore;
       }; */

    true;
  };

  dispatchAction := (action => dispatch(action, update));

  currentView := view(model, dispatchAction^);
  root := render(currentView^) |> Dom.init("app");
};