import Account from "../models/Account";
import {Link, Route, Routes} from "react-router-dom";
import HomeController from "../controllers/HomeController";
import LoginController from "../controllers/LoginController";
import RegisterController from "../controllers/RegisterController";
import ProfileController from "../controllers/ProfileController";
import ReaderController from "../controllers/ReaderController";
import LibrarianController from "../controllers/LibrarianController";
import AdminController from "../controllers/AdminController";

interface Props{
    currentUser: Account | undefined
    logOut: () => void
}

const AppView = ({ currentUser, logOut}: Props) =>{
    return (
        <div>
            <nav className="navbar navbar-expand navbar-dark bg-dark">
                <Link to={"/"} className="navbar-brand">
                    Library System
                </Link>
                <div className="navbar-nav mr-auto">

                    {currentUser?.librarian_acc.lib_id != undefined && (
                        <li className="nav-item">
                            <Link to={"/librarian"} className="nav-link">
                                Librarian Board
                            </Link>
                        </li>
                    )}

                    {currentUser && currentUser?.librarian_acc.lib_id == undefined && currentUser?.reader_acc.phone == undefined && (
                        <li className="nav-item">
                            <Link to={"/admin"} className="nav-link">
                                Admin Board
                            </Link>
                        </li>
                    )}
                    {currentUser?.reader_acc.phone != undefined && (
                        <li className="nav-item">
                            <Link to={"/user"} className="nav-link">
                                Reader Board
                            </Link>
                        </li>
                    )}
                </div>

                {currentUser ? (
                    <div className="navbar-nav ml-auto">
                        <li className="nav-item">
                            <Link to={"/profile"} className="nav-link">
                                {currentUser.name}
                            </Link>
                        </li>
                        <li className="nav-item">
                            <a href="/" className="nav-link" onClick={logOut}>
                                LogOut
                            </a>
                        </li>
                    </div>
                ) : (
                    <div className="navbar-nav ml-auto">
                        <li className="nav-item">
                            <Link to={"/login"} className="nav-link">
                                Login
                            </Link>
                        </li>

                        <li className="nav-item">
                            <Link to={"/register"} className="nav-link">
                                Sign Up
                            </Link>
                        </li>
                    </div>
                )}
            </nav>

            <div className="container mt-3">
                <Routes>
                    <Route path="/" element={<HomeController />} />
                    <Route path="/login" element={<LoginController />} />
                    <Route path="/register" element={<RegisterController />} />
                    <Route path="/profile" element={<ProfileController />} />
                    <Route path="/user" element={<ReaderController />} />
                    <Route path="/librarian" element={<LibrarianController />} />
                    <Route path="/admin" element={<AdminController />} />
                </Routes>
            </div>

        </div>
    );
}
export default AppView