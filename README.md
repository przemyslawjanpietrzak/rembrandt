# Rembrandt
[![CircleCI](https://circleci.com/gh/przemyslawjanpietrzak/rembrandt/tree/develop.svg?style=svg)](https://circleci.com/gh/przemyslawjanpietrzak/rembrandt/tree/develop)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![npm version](https://img.shields.io/npm/v/bs-rembrandt.svg?style=flat)

![alt text](./logo-small.png "Logo")

Simple functional UI framework written in Reasonml.

## Getting started

`yarn add bs-rembrandt`

Create seed project:

`yarn bs-rembrandt init`

Build production files:

`yarn bs-rembrandt build`

Run dev server:

`yarn bs-rembrandt start:bs`

And in another terminal:

`yarn bs-rembrandt start:js`

Run unit tests:

`yarn bs-rembrandt test`

Display all available commands in CLI:

`yarn bs-rembrandt help`

## Example app

```reason
open Rembrandt.Elements;

type model = int;
type action =
  | Add
  | Sub
  | Twice;

let update =
    (model: model, action: action): (model, Command.command('action)) =>
  switch (action) {
  | Add => (model + 1, Command.null)
  | Sub => (model - 1, Command.null)
  | Twice => (model + 1, Command.action(Add))
};

Rembrandt.run(
  ~model=42,
  ~update,
  ~view=
    (model, dispatch) =>
      <div>
        <div id="count"> {string_of_int(model) |> text} </div>
        <button id="plus" onClick={_ => Add |> dispatch}>
          {"+" |> text}
        </button>
        <button id="minus" onClick={_ => Sub |> dispatch}>
          {"-" |> text}
        </button>
        <button id="double" onClick={_ => Twice |> dispatch}>
          {"twice +" |> text}
        </button>
      </div>,
  (),
);
```

## API

### model

Initial store value.

### update

Function for modify model. It takes current model and dispatched action. It returns 2 element tuple with new model and command.

### command

Way to run side effects in asynchronously. `Command.null` wouldn't run anything, `Command.action` will dispatch action asynchronously, `Command.run` will run passed function with `dispatch` as argument.

### view

On every state change result on function will be render on rootNode. Argument `dispatch` should be call with proper `action` on DOM event callback.

### rootId (optional)

String for find rootNode via `document.getElementById`. Default is `app`.

### initAction (optional)

Action to dispatch after first render. Default is `Command.null`.

### middlewares (optional):
List of functions to apply on each state update. Each takes oldModel, newModel and action as arguments. See `Rembrandt.MiddleWares.logger` in `examples/Form.re`. Default is [].

### subscription (optional):
Function that takes current model and dispatch as argument. Allows to dispatch action based on asynchronous source (e.g. websocket) See in `examples/Subscription.re`. Default is `(model, dispatch)=> ()`.

## Shadow Dom
To wrap elements in shadow dom you can use the `<shadowRoot>` element imported from `Rembrandt.Elements` as other components. It will render `<div>` element with shadowRoot. To attach a close shadow DOM use ` <shadowRoot mode=ShadowDomCloseMode>`, however it's not recommended to use it for display model-related data. See `examples/ShadowDom.re`.