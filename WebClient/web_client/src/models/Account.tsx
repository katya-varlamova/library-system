interface Account
{
    id: number,
    name: string,
    login : string,
    token: string,
    admin_acc: {},
    librarian_acc: {
        lib_id: number
    },
    reader_acc: {
        phone: string
    }
}
export default Account
