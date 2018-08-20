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

  test("", () => {
    removeFromSimulateList([None, Some(42), None, None], 0)
      |> expect |> toEqual([ Some(42), None, None])

    removeFromSimulateList([None, Some(42), None, None], 1)
      |> expect |> toEqual([ None, None, None])
  })

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
  });

  test("Removing items", () => {
    let before = [<div key="1"/>, <div key="2"/>, <div key="3"/>, <div key="4"/>, <div key="5"/>, <div key="6"/>]
    let after = [<div key="2"/>, <div key="3"/>, <div key="1"/>]
    let diffs = getDiff(before, after);

    diffs.moves |> List.length |> expect |> toBe(5) |> ignore

    diffs.children
      |> expect
      |> toEqual([
        Some(<div key="1"/>),
        Some(<div key="2"/>),
        Some(<div key="3"/>),
        None,
        None,
        None,
      ])
  });

  test("Removing items in the middel", () => {
    let before = [<div key="1"/>, <div key="2"/>, <div key="3"/>, <div key="4"/>, <div key="5"/>, <div key="6"/>]
    let after = [<div key="1"/>, <div key="2"/>, <div key="4"/>, <div key="6"/>]

    let diffs = getDiff(before, after);

    diffs.moves |> List.length |> expect |> toBe(2) |> ignore;
    diffs.children
      |> expect
      |> toEqual([
        Some(<div key="1"/>),
        Some(<div key="2"/>),
        None,
        Some(<div key="4"/>),
        None,
        Some(<div key="6"/>),
      ])
  })

  test("Inserting items", () => {
    let before = [<div key="1"/>, <div key="2"/>, <div key="3"/>, <div key="4"/>];
    let after = [<div key="1"/>, <div key="2"/>, <div key="3"/>, <div key="4"/>, <div key="5"/>, <div key="6"/>];
    let diffs = getDiff(before, after);

    diffs.moves |> List.length |> expect |> toBe(2) |> ignore;
    diffs.children
      |> expect
      |> toEqual([
        Some(<div key="1"/>),
        Some(<div key="2"/>),
        Some(<div key="3"/>),
        Some(<div key="4"/>),
      ])
  })

  test("Moving items from back to front", () => {
    let before = [<div key="1"/>, <div key="2"/>, <div key="3"/>, <div key="4"/>, <div key="5"/>, <div key="6"/>];
    let after = [<div key="1"/>, <div key="2"/>, <div key="7"/>, <div key="8"/>, <div key="3"/>, <div key="4"/>, <div key="5"/>, <div key="6"/>];
    /* let after = ['a', 'b', 'e', 'f', 'c', 'd', 'g', 'h'] */
    let diffs = getDiff(before, after);
    diffs.moves |> List.length |> expect |> toBe(4) |> ignore;
    diffs.children
      |> expect
      |> toEqual([
        Some(<div key="1"/>),
        Some(<div key="2"/>),
        Some(<div key="3"/>),
        Some(<div key="4"/>),
        Some(<div key="5"/>),
        Some(<div key="6"/>),
      ]);
  })

  test("Moving items from front to back", () => {
    let before = [<div key="1"/>, <div key="2"/>, <div key="3"/>, <div key="4"/>, <div key="5"/>, <div key="6"/>];
    let after = [<div key="1"/>,  <div key="3"/>, <div key="5"/>, <div key="6"/>, <div key="2"/>, <div key="4"/>,];
    let diffs = getDiff(before, after);

    diffs.moves |> List.length |> expect |> toBe(4) |> ignore;
    diffs.children
      |> expect
      |> toEqual([
        Some(<div key="1"/>),
        Some(<div key="2"/>),
        Some(<div key="3"/>),
        Some(<div key="4"/>),
        Some(<div key="5"/>),
        Some(<div key="6"/>),
      ]);
  })

});
