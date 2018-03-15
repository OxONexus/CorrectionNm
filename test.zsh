function diff_nm {
	nvim -d <(./ft_nm $1 ) <(nm $1)
}

function diff_otool {
	nvim -d  <(./ft_otool $1) <(otool -t $1)
}
