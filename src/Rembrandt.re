open Main;

type appParams('model, 'action) = {
    view: ('model, ('action) => 'model) => Main.node,
    update: ('model, 'action) => 'model,
    model: 'model,
};

let dispatch = (action, model, update) => {
    update(model, action)
}
let run = (~view, ~model, ~update) => {
    let root = ref(Dom.createElement("div"));
    let currentView = ref(<div></div>);
    let dispatchAction = ref(_ => false);
    let currentModel = ref(model);

    let dispatch = (action, model, update) => {
        currentModel := update(currentModel^, action);
        let updatedView = view(currentModel^, dispatchAction^);
        VirtualDom.setPositions(~node=updatedView, ~initialPosition=0);
        let root = updatedView |> Main.render |> Dom.update("app");
        let diff = VirtualDom.getDiff(~oldNode=currentView^, ~newNode=Some(updatedView));
        VirtualDomPatch.applyPatches(root, diff);
        true;
    }

    dispatchAction := action => dispatch(action, model, update);

    currentView := view(model, dispatchAction^);
    root := Main.render(currentView^)
        |> Dom.init("app")
}


