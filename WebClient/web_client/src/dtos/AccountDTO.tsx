
interface AccountDto
{
    id: number,
    name: string,
    token: string,
    admin_acc: {},
    librarian_acc: {
        lib_id: number
    },
    reader_acc: {
        phone: string
    }
}
export default AccountDto
