#!/bin/bash

output_file="all"
> $output_file  # 出力ファイルをクリア

# .cファイルを指定したパスを除外して検索
find . -type f -name "*.c" \
    ! -path "./db_model/templates/go/go.go" \
    ! -path "./graph/generated.go" \
    ! -path "./libft/*" | while read -r file; do
    echo "File: $file" >> $output_file
    awk '{print FNR ": " $0}' "$file" >> $output_file
    echo "" >> $output_file
done