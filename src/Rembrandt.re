type appParams('model, 'action) = {
    view: ('model, ('action) => 'model) => Main.node,
    update: ('model, 'action) => 'model,
    model: 'model,
};


let dispatch = (action, model, update) => {
    update(model, action)
}
let appRun = (~view, ~model, ~update) => {
    let currentModel = ref(model)
    let dispatch = (action, model, update) => {
        let updatedModel = update(model, action);
        currentModel := updatedModel;
        /* TODO: rerender */ 
        updatedModel;
    }

    let dispatchAction = action => dispatch(action, currentModel, update);

    view(model, dispatchAction)
        |> Main.render;
}


