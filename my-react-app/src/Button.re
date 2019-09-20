[@react.component]
let make = (~text, ~css, ~handleAction) => {
  let handleClick = event => {
    ReactEvent.Mouse.preventDefault(event);
    handleAction();
  };

  <a className=css href="#" onClick=handleClick> {React.string(text)} </a>;
};