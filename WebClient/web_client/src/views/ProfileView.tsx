
import Account from "../models/Account";
interface Props{
    user: Account
    library? : string
}

const ProfileView = ({ user, library }: Props) =>{
    return (
        <div className="container">
            <div>
                <header className="jumbotron">
                    <h3>
                        <strong>{user.login}</strong> Profile
                    </h3>
                </header>
                <p>
                    <strong>User name:</strong>{" "}
                    {user.name}
                </p>
                <p>
                    <strong>Id:</strong>{" "}
                    {user.id}
                </p>
                {(user.reader_acc.phone == undefined && user.librarian_acc.lib_id == undefined) ?
                    <p>
                        <strong>role:</strong>{" "}
                        admin
                    </p>
                    : null}

                {(user.reader_acc.phone != undefined) ?
                    <div>
                        <p>
                            <strong>role:</strong>{" "}
                            reader
                        </p>
                        <p>
                            <strong>phone:</strong>{" "}
                            {user.reader_acc.phone}
                        </p>
                    </div>
                    : null}

                {(user.librarian_acc.lib_id != undefined) ?
                    <div>
                        <p>
                            <strong>role:</strong>{" "}
                            librarian
                        </p>
                        <p>
                            <strong>Library:</strong>{" "}
                            {library}
                        </p>
                    </div>
                    : null}
            </div>
        </div>
    );
}
export default ProfileView