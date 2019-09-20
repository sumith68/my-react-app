type t = {
  id: int,
  text: string,
  author: string,
};

let make = (~id, ~text, ~author) => {id, text, author};

let id = t => t.id;

let text = t => t.text;

let author = t => t.author;