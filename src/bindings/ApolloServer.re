[@bs.module "apollo-server"] [@bs.new]
external makeApolloServer :
  {
    .
    "options": Js.Nullable.t(Js.t({..})),
    "typeDefs": Js.Nullable.t(string),
    "resolvers": Js.Nullable.t(Js.t({..})),
    "engine": Js.Nullable.t(bool),
  } =>
  'a =
  "ApolloServer";

[@bs.send.pipe: 'a]
external listen : {. "port": Js.Nullable.t(int)} => Js.Promise.t('a) = "";

let createApolloServer =
    (~options=?, ~typeDefs=?, ~resolvers=?, ~engine=?, ()) => {
  let apolloServerOptions = {
    "options": Js.Nullable.fromOption(options),
    "typeDefs": Js.Nullable.fromOption(typeDefs),
    "resolvers": Js.Nullable.fromOption(resolvers),
    "engine": Js.Nullable.fromOption(engine),
  };
  makeApolloServer(apolloServerOptions);
};