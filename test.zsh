function diff_nm {
	vim -d <(./ft_nm $1 ) <(nm $1)
}

function diff_otool {
	vim -d  <(./ft_otool $1) <(otool -t $1)
}
