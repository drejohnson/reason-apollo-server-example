type queryString;

type graphqlServer;

type gql_ = (. string) => queryString;

type options;

[@bs.deriving abstract]
type response = {url: string};

[@bs.deriving abstract]
type apolloServerProps = {
  options: Js.nullable(options),
  typeDefs: Js.nullable(queryString),
  resolvers: Js.nullable(TodoType.resolvers),
  engine: Js.nullable(bool),
};

[@bs.deriving abstract]
type listenProps = {port: int};

[@bs.module "apollo-server"] external gql: gql_ = "gql";

[@bs.module "apollo-server"] [@bs.new]
external makeApolloServer: apolloServerProps => graphqlServer = "ApolloServer";

[@bs.send]
external listen: (graphqlServer, listenProps) => Js.Promise.t('a) = "";

let createApolloServer =
    (~options=?, ~typeDefs=?, ~resolvers=?, ~engine=?, ()) => {
  let apolloServerOptions =
    apolloServerProps(
      ~options=Js.Nullable.fromOption(options),
      ~typeDefs=Js.Nullable.fromOption(typeDefs),
      ~resolvers=Js.Nullable.fromOption(resolvers),
      ~engine=Js.Nullable.fromOption(engine),
    );
  makeApolloServer(apolloServerOptions);
};