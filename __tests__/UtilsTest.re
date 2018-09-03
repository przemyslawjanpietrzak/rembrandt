open Jest;

open Utils;

describe("Utils", () => {
  open Expect;

  test("removeFromList", () => {
    removeFromList([0,1,2,3,4,5], 4) |> expect |> toEqual([0,1,2,3,5]) |> ignore;
    removeFromList([0], 0) |> expect |> toEqual([]) |> ignore;
    removeFromList([], 0) |> expect |> toEqual([]) |> ignore;
    removeFromList([0, 1, 2], 3) |> expect |> toEqual([0, 1, 2]);
  });

  test("replaceInList", () => {
    replaceInList([0, 1, 2], 0, 42) |> expect |> toEqual([42, 1, 2]) |> ignore;
    replaceInList([0, 1, 2], 1, 42) |> expect |> toEqual([0, 42, 2]) |> ignore;
    replaceInList([0, 1, 2], 4, 42) |> expect |> toEqual([0, 1, 2]);
  });
});