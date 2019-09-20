type t;

let make: (~id: int, ~text: string, ~author: string) => t;

let id: t => int;

let text: t => string;

let author: t => string;