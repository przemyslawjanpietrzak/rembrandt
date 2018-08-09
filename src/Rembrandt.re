type appParams('model, 'action) = {
    view: ('model, ('action) => 'model) => Dom.domElement,
    update: ('model, 'action) => 'model,
    model: 'model,
};

let dispatch = (action, model, update) => {
    update(model, action)
}
let run = (~view, ~model, ~update) => {
    let currentModel = model
    let dispatch = (action, model, update) => {
        /* currentModel := updatedModel; TODO:*/
        /* TODO: rerender */
        update(model, action);

    }

    let dispatchAction = action => dispatch(action, currentModel, update);

    view(model, dispatchAction)
        |> Main.render;
}


