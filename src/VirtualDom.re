open Main;
open Dom;

type nullableNode = Node | Null;

type patch = {
    type: string,
    content: node
}

let isIgnoredNode = node => false; /* TODO: */


let diffProps = (oldNode: node, newNode: node) => {

  let changedProps = oldNode.attributes
   |> List.filter(
      ((oldKey, oldValue)) => List.exist(((newKey, newValue)) => newKey === oldKey && newValue !== oldValue, newNode.attributes),
    )

  let newProps = newNode.attributes
    |> List.filter(
      ((newKey, _)) => !List.exist(((oldKey, _)) => oldKey !== newKey, oldNode.attributes)
    )

    [...changedProps, ...newProps]
}

let walker = (oldNode, newNode: optional(node), index) => {
   let currentPathch = [];
   switch (newNode) {
    | Null =>
    | Some(node) => {
         /* TextNode content replacing */
        if (node.name === Text && oldNode.name === Text) {
            if (node.text !== oldNode.text) {
               currentPatch = [...currentPatch, { type: "text", content: node }];
            }
        } else if (node.name === oldNode.name) {
            /* Diff props */
            let propsPatches = diffProps(oldNode, node);
            if (!propsPatches.empty) {
               currentPatch = [...currentPatch, type: "props", props: propsPatches }];
            }
        }
      }
   }
}
/*
   var _ = require('./util')
var patch = require('./patch')
var listDiff = require('list-diff2')

function diff (oldTree, newTree) {
  var index = 0
  var patches = {}
  dfsWalk(oldTree, newTree, index, patches)
  return patches
}

function dfsWalk (oldNode, newNode, index, patches) {
  var currentPatch = []

  // Node is removed.
  if (newNode === null) {
    // Real DOM node will be removed when perform reordering, so has no needs to do anthings in here
  // TextNode content replacing
  } else if (_.isString(oldNode) && _.isString(newNode)) {
    if (newNode !== oldNode) {
      currentPatch.push({ type: patch.TEXT, content: newNode })
    }
  // Nodes are the same, diff old node's props and children
  } else if (
      oldNode.tagName === newNode.tagName &&
      oldNode.key === newNode.key
    ) {
    // Diff props
    var propsPatches = diffProps(oldNode, newNode)
    if (propsPatches) {
      currentPatch.push({ type: patch.PROPS, props: propsPatches })
    }
    // Diff children. If the node has a `ignore` property, do not diff children
    if (!isIgnoreChildren(newNode)) {
      diffChildren(
        oldNode.children,
        newNode.children,
        index,
        patches,
        currentPatch
      )
    }
  // Nodes are not the same, replace the old node with new node
  } else {
    currentPatch.push({ type: patch.REPLACE, node: newNode })
  }

  if (currentPatch.length) {
    patches[index] = currentPatch
  }
}

function diffChildren (oldChildren, newChildren, index, patches, currentPatch) {
  var diffs = listDiff(oldChildren, newChildren, 'key')
  newChildren = diffs.children

  if (diffs.moves.length) {
    var reorderPatch = { type: patch.REORDER, moves: diffs.moves }
    currentPatch.push(reorderPatch)
  }

  var leftNode = null
  var currentNodeIndex = index
  _.each(oldChildren, function (child, i) {
    var newChild = newChildren[i]
    currentNodeIndex = (leftNode && leftNode.count)
      ? currentNodeIndex + leftNode.count + 1
      : currentNodeIndex + 1
    dfsWalk(child, newChild, currentNodeIndex, patches)
    leftNode = child
  })
}


function isIgnoreChildren (node) {
  return (node.props && node.props.hasOwnProperty('ignore'))
}

module.exports = diff /*
