open Todo;

let server =
  ApolloServer.createApolloServer(
    ~typeDefs,
    ~resolvers=Resolvers.resolvers,
    (),
  );

server->(ApolloServer.listen(ApolloServer.listenProps(~port=4444)))
|> Js.Promise.then_(res =>
     Js.log("Server ready at " ++ res##url) |> Js.Promise.resolve
   );