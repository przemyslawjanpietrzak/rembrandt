let removeFromList = (items: list('a), index: int): list('a) => {
  let rec removeFromListAcc = (items, index, acc) =>
    switch (items) {
    | [] => acc
    | [head, ...tail] =>
      if (index === 0) {
        List.append(acc, tail);
      } else {
        removeFromListAcc(tail, index - 1, List.append(acc, [head]));
      }
    };
  removeFromListAcc(items, index, []);
};

let replaceInList = (items: list('a), index: int, item: 'a): list('a) => {
  let rec replaceInListAcc = (items, index, acc) =>
    switch (items) {
    | [] => acc
    | [head, ...tail] =>
      if (index === 0) {
        acc->List.append([item])->List.append(tail);
      } else {
        replaceInListAcc(tail, index - 1, List.append(acc, [head]));
      }
    };
  replaceInListAcc(items, index, []);
};

module StringMap =
  Map.Make({
    type t = string;
    let compare = compare;
  });

module IntMap =
  Map.Make({
    type t = int;
    let compare = compare;
  });
