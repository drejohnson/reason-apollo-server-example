open TodoTypeDefs;

open TodoResolvers;

let server = ApolloServer.createApolloServer(~typeDefs, ~resolvers, ());

server
|> ApolloServer.listen({"port": Js.Nullable.return(8888)})
|> Js.Promise.then_(url =>
     Js.log("Server ready at " ++ url##url) |> Js.Promise.resolve
   );