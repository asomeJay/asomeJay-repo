import express from "express";
import morgan from "morgan";
import helmet from "helmet";
import cookie_parser from "cookie-parser";
import body_parser from "body-parser";
import routes from "./routes";
import userRouter from "./Router/userRouter";
import videoRouter from "./Router/videoRouter";
import globalRouter from "./Router/globalRouter";

const app = express();

app.use(cookie_parser());
app.use(body_parser.urlencoded({extended:true}));
app.use(body_parser.json());
app.use(helmet());
app.use(morgan("dev"));

app.use(routes.home, globalRouter);
app.use(routes.users, userRouter);
app.use(routes.videos, videoRouter);

export default app;
