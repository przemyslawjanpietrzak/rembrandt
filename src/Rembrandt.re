type appParams('model, 'action) = {
    view: ('model, ('action) => 'model) => Dom.domElement,
    update: ('model, 'action) => 'model,
    model: 'model,
};

let dispatch = (action, model, update) => {
    update(model, action)
}
let run = (~view, ~model, ~update) => {
    let dispatch = (action, model, update) => {
        /* TODO: rerender */
        update(model, action);
    }

    let dispatchAction = action => dispatch(action, model, update);

    view(model, dispatchAction)
        |> Main.render;
}


