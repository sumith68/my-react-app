[@react.component]
let make = (~quote) =>
  <>
    <p className="mr-8"> {React.string(quote |> Quote.text)} </p>
    <p className="text-xs"> {React.string(quote |> Quote.author)} </p>
  </>;