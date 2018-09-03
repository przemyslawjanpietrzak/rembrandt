open Jest;

open Common;

open Positions;
open Diff;
open DiffProps;

/* let getPatchType = patches => List.nth(patches, 0).patchType; */

describe("Test diff algorithm", () => {
  open Expect;

  test("empty diff", () => {
    diffProps(
      <div key="1"></div>,
      <div key="1"></div>,
    ) |> expect |> toEqual([])
  });

  test("updated props", () => {
    diffProps(
      <div key="1"></div>,
      <div key="2"></div>,
    ) |> expect |> toEqual([("key", "2")])
  });

  test("new props", () => {
    diffProps(
      <div key="1"></div>,
      <div key="1" id="new"></div>,
    ) |> expect |> toEqual([("id", "new")])
  })
});