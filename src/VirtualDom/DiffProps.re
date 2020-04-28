open ElementsTypes;
open ElementFactory;

let diffProps = (oldNode: node, newNode: node) => {
  let changedProps =
    oldNode.attributes
    |> List.filter(((oldKey, oldValue)) =>
         List.exists(
           ((newKey, newValue)) => oldKey == newKey && oldValue != newValue,
           newNode.attributes,
         )
       )
    |> List.map(((oldKey, _)) =>
         List.find(((newKey, _)) => oldKey == newKey, newNode.attributes)
       );

  let newProps =
    newNode.attributes
    |> List.filter(((newKey, _)) =>
         !List.exists(((oldKey, _)) => oldKey == newKey, oldNode.attributes)
       );
  List.append(changedProps, newProps);
};
