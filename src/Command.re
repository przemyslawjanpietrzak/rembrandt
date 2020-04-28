type commandType =
  | CAction
  | Run
  | Null;

type dispatchAction('action) = 'action => unit;

type commandCallback('action) = dispatchAction('action) => unit;

type command('action) = {
  commandAction: option('action),
  callback: option(commandCallback('action)),
  commandType,
};

let null: command('None) = {
  commandAction: None,
  callback: None,
  commandType: Null,
};

let action = (action: 'action): command('action) => {
  commandAction: Some(action),
  callback: None,
  commandType: CAction,
};

let run = (callback: commandCallback('action)): command('action) => {
  commandAction: None,
  callback: Some(callback),
  commandType: Run,
};
