open Jest;
open Main;
open VirtualDom;

describe("Test diff algorithm", () => {
  open Expect;

  test("Node replacing",  () => {
    let oldNode = <div>
      <div/>
      <div/>
      <div/>
    </div>;
    let newNode = <div>
      <div/>
      <span/>
      <div/>
    </div>;
    
    let diff = getDiff(oldNode, Some(newNode));
    let a =2
    a |> expect |> toEqual(2);
    /* diff -> Hashtbl.find(2) |> expect |> toEqual({ patchType: Props, attributes: None, content: None, moves: [] }) */
    /* patches[2][0].type.should.be.equal(patch.REPLACE) */
  });

});