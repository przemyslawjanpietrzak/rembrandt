open Jest;

open Main;
open ListDiff;

type item = { key: string };

describe("ListDiff", () => {
  open Expect;

  test("getItemKey", () => {
    getItemKey(<div key="1"/>)
      |> expect
      |> toEqual(Some("1"));
  })
/* 
  test("", () => {
    removeFromSimulateList1(
      ref[None, Some(42), None, None]),
      0, false
    ) |> expect  |> toEqual(ref([ Some(42), None, None]),)
  }) */

  test("Making map from list with string key", () => {
    let list = [
      <div key="1"/>,
      <div key="2"/>,
      <div key="3"/>,
    ];
    let { keyIndex } = makeKeyIndexAndFree(list);

    keyIndex
      |> Hashtbl.length
      |> expect
      |> toEqual(3);

    Hashtbl.find(keyIndex, "1")
      |> expect
      |> toEqual(0);

    Hashtbl.find(keyIndex, "2")
      |> expect
      |> toEqual(1);

    Hashtbl.find(keyIndex, "3")
      |> expect
      |> toEqual(2);
  })

  test("Removing items", () => {
    let before = [<div key="1"/>, <div key="2"/>, <div key="3"/>, <div key="4"/>, <div key="5"/>, <div key="6"/>]
    let after = [<div key="2"/>, <div key="3"/>, <div key="1"/>]
    let diffs = getDiff(before, after);

    /* 5 |> expect |> toBe(4); */
      diffs.moves
      |> List.length
      |> expect
      |> toBe(5)
    /* diffs.moves.length.should.be.equal(5) */
    /* perform(before, diffs)
    diffs.children.should.be.deep.equal([{id: 1}, {id: 2}, {id: 3}, null, null, null])
    assertListEqual(after, before) */
  })
});
