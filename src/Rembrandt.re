open Common;

type appParams('model, 'action) = {
    view: ('model, ('action) => 'model) => node,
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
        let diff = VirtualDom.getDiff(~oldNode=currentView^, ~newNode=Some(updatedView));
        VirtualDom.patch(root^, diff);
        true;
    }

    dispatchAction := action => dispatch(action, model, update);

    currentView := view(model, dispatchAction^);
    root := render(currentView^)
        |> Dom.init("app")
}
