open Belt;

let rid = () => Js.Math.random_int(0, 10000);

type state = {
  quotes: list(Quote.t),
  deleteQueue: Map.Int.t(Js.Global.timeoutId),
};

let defaultState = {
  quotes: [
    Quote.make(
      ~id=rid(),
      ~text="Simplicity is prerequisite for reliability.",
      ~author="Edsger W.Dijkstra",
    ),
    Quote.make(
      ~id=rid(),
      ~text="Simplicity is prerequisite for reliability.",
      ~author="Edsger W.Dijkstra",
    ),
    Quote.make(
      ~id=rid(),
      ~text="Simplicity is prerequisite for reliability.",
      ~author="Edsger W.Dijkstra",
    ),
  ],
  deleteQueue: Map.Int.empty,
};

[@react.component]
let make = () => {
  let (state, setState) = React.useState(() => defaultState);

  let quoteCss = "mb-1 p-4 shadow-xl bg-blue-200 text-gray-600";
  let alertCss = "mb-1 pt-4 shadow-xl bg-red-200 text-gray-800";

  let deleteQueued = id => {
    let quotes = state.quotes->List.keep(x => id != Quote.id(x));

    state.deleteQueue
    ->Map.Int.get(id)
    ->Belt.Option.map(Js.Global.clearTimeout)
    |> ignore;

    let deleteQueue = state.deleteQueue->Map.Int.remove(id);

    setState(_state => {quotes, deleteQueue});
  };

  let addToDeleteQueue = id => {
    let timeoutId = Js.Global.setTimeout(() => deleteQueued(id), 10000);
    setState(state =>
      {...state, deleteQueue: state.deleteQueue->Map.Int.set(id, timeoutId)}
    );
  };

  let restore = id => {
    state.deleteQueue
    ->Map.Int.get(id)
    ->Belt.Option.map(Js.Global.clearTimeout)
    |> ignore;

    let deleteQueue = state.deleteQueue->Map.Int.remove(id);
    setState(state => {...state, deleteQueue});
  };

  let renderWarning = (i, quote) =>
    <div className="mb-4" key={string_of_int(i)}>
      <Card className=alertCss>
        <p className="text-center mb-4">
          {React.string("This quote is going to be deleted")}
        </p>
        <div className="mb-8 flex justify-center">
          <Button
            css="py-2 px-4 bg-red-600 text-gray-200 mr-4"
            text="Delete immediately"
            handleAction={() => quote |> Quote.id |> deleteQueued}
          />
          <Button
            css="py-2 px-4 bg-blue-600 text-gray-200"
            text="Restore Quote"
            handleAction={() => quote |> Quote.id |> restore}
          />
        </div>
        <div className="h-2 bg-red-600 animate-delete-countdown" />
      </Card>
    </div>;

  let renderCardItem = (i, quote) =>
    <div key={string_of_int(i)} className="mb-4">
      <Card className=quoteCss> <QuoteView quote /> </Card>
      <Button
        css="text-red-600 hover:underline"
        text="Delete"
        handleAction={() => quote |> Quote.id |> addToDeleteQueue}
      />
    </div>;

  let isQueueForDeletion = i =>
    state.deleteQueue->Map.Int.get(i)->Option.isSome;

  let renderCard = (i, quote) =>
    isQueueForDeletion(quote |> Quote.id)
      ? renderWarning(i, quote) : renderCardItem(i, quote);

  <div className="m-4">
    {state.quotes->List.mapWithIndex(renderCard)->List.toArray->React.array}
  </div>;
};