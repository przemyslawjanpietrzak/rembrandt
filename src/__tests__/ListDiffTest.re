open Jest;

open Utils;
open Common;
open ListDiff;

describe("ListDiff", () => {
  open Expect;

  test("Making map from list with string key", () => {
    let list = [
      <div key="1"/>,
      <div key="2"/>,
      <div key="3"/>,
    ];
    let { keyIndex } = makeKeyIndexAndFree(list);

    StringMap.find("1", keyIndex)
      |> expect
      |> toEqual(0)
      |> ignore;

    StringMap.find("2", keyIndex)
      |> expect
      |> toEqual(1)
      |> ignore;

    StringMap.find("3", keyIndex)
      |> expect
      |> toEqual(2);
  });

  test("Removing items", () => {
    let before = [<div key="1"/>, <div key="2"/>, <div key="3"/>, <div key="4"/>, <div key="5"/>, <div key="6"/>]
    let after = [<div key="2"/>, <div key="3"/>, <div key="1"/>]
    let diffs = getListDiff(before, after);

    diffs.children
      |> expect
      |> toEqual([
        Some(<div key="1"/>),
        Some(<div key="2"/>),
        Some(<div key="3"/>),
        None,
        None,
        None,
      ]) |> ignore;
      diffs.moves
      |> expect
      |> toEqual([
        { index: 3, moveType: Remove, item: None },
        { index: 3, moveType: Remove, item: None },
        { index: 3, moveType: Remove, item: None },
        { index: 0, moveType: Remove, item: None },
        { index: 2, moveType: Insert, item: Some(<div key="1"/>), },
      ]);
  });

  test("Removing items in the middle", () => {
    let before = [<div key="1"/>, <div key="2"/>, <div key="3"/>, <div key="4"/>, <div key="5"/>, <div key="6"/>]
    let after = [<div key="1"/>, <div key="2"/>, <div key="4"/>, <div key="6"/>]

    let diffs = getListDiff(before, after);

    diffs.moves |> expect |> toEqual([ { index: 2, moveType: Remove, item: None }, { index: 3, moveType: Remove, item: None } ]) |> ignore;
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
    let diffs = getListDiff(before, after);

    diffs.moves
      |> expect
      |> toEqual([
        { index: 2, moveType: Insert, item: Some(<div key="5"/>) },
        { index: 3, moveType: Insert, item: Some(<div key="6"/>) },
      ])
      |> ignore;
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
    let diffs = getListDiff(before, after);

    diffs.moves
      |> expect
      |> toEqual([
        { index: 2, item: Some(<div key="5"/>), moveType: Insert },
        { index: 3, item: Some(<div key="6"/>), moveType: Insert },
        { index: 6, item: Some(<div key="7"/>), moveType: Insert },
        { index: 7, item: Some(<div key="8"/>), moveType: Insert },
        { index: 9, item: None, moveType: Remove },
        { index: 8, item: None, moveType: Remove },
      ])
      |> ignore;
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
    let diffs = getListDiff(before, after);

    diffs.moves |> List.length |> expect |> toBe(4) |> ignore;
    diffs.moves
    |> expect
    |> toEqual([
      { index: 1, item: None, moveType: Remove },
      { index: 2, item: None, moveType: Remove },
      { index: 3, item: Some(<div key="2"/>), moveType: Insert },
      { index: 3, item: Some(<div key="4"/>), moveType: Insert },
    ])
    |> ignore;
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
