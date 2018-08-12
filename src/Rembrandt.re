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

    let dispatch = (action, model, update) => {
        let updatedModel = update(model, action);
        let updatedView = view(updatedModel, dispatchAction);
        VirtualDom.updateElement(
            ~parent=root^,
            ~newNode=updatedView,
            ~oldNode=currentView^,
            ~index=0,
        );
        true;
    }

    dispatchAction := action => dispatch(action, model, update);

    currentView := view(model, dispatchAction);
    root := Main.render(currentView^)
        |> Dom.init("app")
}


