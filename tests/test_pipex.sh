#!/bin/bash

# Couleurs pour l'affichage
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Compteurs
PASSED=0
FAILED=0
TOTAL=0

# Fonction de test
run_test() {
	local test_name=$1
	local infile=$2
	local cmd1=$3
	local cmd2=$4
	local outfile=$5
	local expected=$6

	TOTAL=$((TOTAL + 1))
	echo -e "${YELLOW}Test $TOTAL: $test_name${NC}"

	# Exécuter avec shell (référence)
	eval "cat $infile | $cmd1 | $cmd2 > /tmp/shell_out.txt" 2>/dev/null
	shell_result=$?

	# Exécuter avec pipex (si implémenté)
	if [ -f ./pipex ]; then
		./pipex "$infile" "$cmd1" "$cmd2" "$outfile" 2>/dev/null
		pipex_result=$?
		
		# Comparer résultats
		if [ -f "$outfile" ]; then
			if diff -q /tmp/shell_out.txt "$outfile" > /dev/null 2>&1; then
				echo -e "${GREEN}✓ PASS${NC}"
				PASSED=$((PASSED + 1))
				rm -f "$outfile"
			else
				echo -e "${RED}✗ FAIL (diff output)${NC}"
				FAILED=$((FAILED + 1))
				echo "Expected:"
				cat /tmp/shell_out.txt | head -3
				echo "Got:"
				cat "$outfile" | head -3
				rm -f "$outfile"
			fi
		else
			echo -e "${RED}✗ FAIL (no output file)${NC}"
			FAILED=$((FAILED + 1))
		fi
	else
		# Si pipex n'existe pas, juste afficher la référence
		echo "Reference output:"
		cat /tmp/shell_out.txt | head -3
		echo "(pipex executable not found)"
	fi
	echo ""
}

# Créer fichiers de test
create_test_files() {
	# Fichier simple avec texte
	cat > /tmp/test_input.txt << 'EOF'
apple
banana
cherry
date
elderberry
EOF

	# Fichier avec nombres
	cat > /tmp/test_numbers.txt << 'EOF'
3
1
4
1
5
9
2
6
EOF

	# Fichier avec chemins
	cat > /tmp/test_paths.txt << 'EOF'
/usr/bin/ls
/bin/cat
/usr/local/bin/ruby
/opt/homebrew/bin/python3
EOF

	# Fichier avec guillemets et espaces
	cat > /tmp/test_quotes.txt << 'EOF'
"hello world"
'single quotes'
mixed "and" 'quotes'
EOF

	# Fichier de configuration
	cat > /tmp/test_config.txt << 'EOF'
# Configuration file
user=john
password=secret123
host=localhost
port=8080
EOF

	# Fichier CSV
	cat > /tmp/test_csv.txt << 'EOF'
id,name,age,city
1,Alice,30,Paris
2,Bob,25,London
3,Charlie,35,Berlin
4,Diana,28,Madrid
EOF

	# Fichier avec caractères spéciaux
	cat > /tmp/test_special.txt << 'EOF'
special@char!
with#hash$sign
and%percent^marks
EOF

	# Grand fichier pour les performances
	seq 1 1000 > /tmp/test_large.txt

	echo "Test files created"
}

# Nettoyer avant
rm -f /tmp/test_output*.txt /tmp/shell_out.txt

# Créer les fichiers de test
create_test_files

echo -e "${YELLOW}======== PIPEX TEST SUITE ========${NC}\n"

# ========== TESTS DE BASE ==========
echo -e "${YELLOW}>>> TESTS DE BASE (2 commandes)${NC}\n"

run_test "cat | wc -l" \
	/tmp/test_input.txt \
	"cat" \
	"wc -l" \
	/tmp/test_out1.txt

run_test "cat | grep a" \
	/tmp/test_input.txt \
	"cat" \
	"grep a" \
	/tmp/test_out2.txt

run_test "cat | sort" \
	/tmp/test_input.txt \
	"cat" \
	"sort" \
	/tmp/test_out3.txt

run_test "cat | sort | uniq" \
	/tmp/test_numbers.txt \
	"sort" \
	"uniq" \
	/tmp/test_out4.txt

# ========== TESTS AVEC AWK ==========
echo -e "${YELLOW}>>> TESTS AVEC AWK${NC}\n"

run_test "cat | awk (print NF)" \
	/tmp/test_csv.txt \
	"cat" \
	"awk '{print NF}'" \
	/tmp/test_awk1.txt

run_test "cat | awk (print \$2)" \
	/tmp/test_csv.txt \
	"cat" \
	"awk '{print \$2}'" \
	/tmp/test_awk2.txt

run_test "cat | awk (skip header)" \
	/tmp/test_csv.txt \
	"cat" \
	"awk 'NR>1 {print \$0}'" \
	/tmp/test_awk3.txt

run_test "cat | awk (BEGIN/END)" \
	/tmp/test_numbers.txt \
	"cat" \
	"awk 'BEGIN {sum=0} {sum+=\$1} END {print sum}'" \
	/tmp/test_awk4.txt

# ========== TESTS AVEC GREP ==========
echo -e "${YELLOW}>>> TESTS AVEC GREP${NC}\n"

run_test "cat | grep -E" \
	/tmp/test_input.txt \
	"cat" \
	"grep -E 'e$'" \
	/tmp/test_grep1.txt

run_test "cat | grep -v" \
	/tmp/test_input.txt \
	"cat" \
	"grep -v apple" \
	/tmp/test_grep2.txt

run_test "cat | grep -i" \
	/tmp/test_input.txt \
	"cat" \
	"grep -i APPLE" \
	/tmp/test_grep3.txt

run_test "cat | grep -c" \
	/tmp/test_config.txt \
	"cat" \
	"grep -c '='" \
	/tmp/test_grep4.txt

# ========== TESTS AVEC SED ==========
echo -e "${YELLOW}>>> TESTS AVEC SED${NC}\n"

run_test "cat | sed (substitution)" \
	/tmp/test_input.txt \
	"cat" \
	"sed 's/a/A/g'" \
	/tmp/test_sed1.txt

run_test "cat | sed (delete lines)" \
	/tmp/test_config.txt \
	"cat" \
	"sed '/^#/d'" \
	/tmp/test_sed2.txt

run_test "cat | sed (number lines)" \
	/tmp/test_input.txt \
	"cat" \
	"sed 's/^/LINE: /'" \
	/tmp/test_sed3.txt

# ========== TESTS AVEC SORT ET UNIQ ==========
echo -e "${YELLOW}>>> TESTS AVEC SORT/UNIQ${NC}\n"

run_test "cat | sort -n" \
	/tmp/test_numbers.txt \
	"cat" \
	"sort -n" \
	/tmp/test_sort1.txt

run_test "cat | sort | uniq -c" \
	/tmp/test_numbers.txt \
	"cat" \
	"sort | uniq -c" \
	/tmp/test_sort2.txt

run_test "cat | sort -r" \
	/tmp/test_input.txt \
	"cat" \
	"sort -r" \
	/tmp/test_sort3.txt

# ========== TESTS AVEC HEAD/TAIL ==========
echo -e "${YELLOW}>>> TESTS AVEC HEAD/TAIL${NC}\n"

run_test "cat | head -n 3" \
	/tmp/test_input.txt \
	"cat" \
	"head -n 3" \
	/tmp/test_head1.txt

run_test "cat | tail -n 2" \
	/tmp/test_input.txt \
	"cat" \
	"tail -n 2" \
	/tmp/test_tail1.txt

run_test "cat | head -n 3 | tail -n 1" \
	/tmp/test_input.txt \
	"head -n 3" \
	"tail -n 1" \
	/tmp/test_head_tail.txt

# ========== TESTS AVEC WC ==========
echo -e "${YELLOW}>>> TESTS AVEC WC${NC}\n"

run_test "cat | wc -c" \
	/tmp/test_input.txt \
	"cat" \
	"wc -c" \
	/tmp/test_wc1.txt

run_test "cat | wc -w" \
	/tmp/test_input.txt \
	"cat" \
	"wc -w" \
	/tmp/test_wc2.txt

run_test "cat | wc -l" \
	/tmp/test_input.txt \
	"cat" \
	"wc -l" \
	/tmp/test_wc3.txt

# ========== TESTS AVEC CUT ==========
echo -e "${YELLOW}>>> TESTS AVEC CUT${NC}\n"

run_test "cat | cut -d',' -f2" \
	/tmp/test_csv.txt \
	"cat" \
	"cut -d',' -f2" \
	/tmp/test_cut1.txt

run_test "cat | cut -c 1-5" \
	/tmp/test_input.txt \
	"cat" \
	"cut -c 1-5" \
	/tmp/test_cut2.txt

# ========== TESTS AVEC TR ==========
echo -e "${YELLOW}>>> TESTS AVEC TR${NC}\n"

run_test "cat | tr 'a' 'A'" \
	/tmp/test_input.txt \
	"cat" \
	"tr 'a' 'A'" \
	/tmp/test_tr1.txt

run_test "cat | tr -d '0-9'" \
	/tmp/test_numbers.txt \
	"cat" \
	"tr -d '\\n'" \
	/tmp/test_tr2.txt

# ========== TESTS AVEC COMBINAISONS COMPLEXES ==========
echo -e "${YELLOW}>>> TESTS AVEC COMBINAISONS COMPLEXES${NC}\n"

run_test "grep | awk" \
	/tmp/test_csv.txt \
	"grep -v id" \
	"awk -F',' '{print \$2}'" \
	/tmp/test_complex1.txt

run_test "cat | sed | sort" \
	/tmp/test_config.txt \
	"grep '='" \
	"cut -d'=' -f1 | sort" \
	/tmp/test_complex2.txt

run_test "cat | awk | sort | uniq" \
	/tmp/test_numbers.txt \
	"awk '{print \$1 % 2}'" \
	"sort | uniq -c" \
	/tmp/test_complex3.txt

# ========== AFFICHAGE DES RÉSULTATS ==========
echo -e "${YELLOW}======== RÉSULTATS ========${NC}"
echo -e "Total tests:  $TOTAL"
echo -e "${GREEN}Passed:       $PASSED${NC}"
echo -e "${RED}Failed:       $FAILED${NC}"

PERCENTAGE=$((PASSED * 100 / TOTAL))
echo -e "Success rate: ${PERCENTAGE}%"

# Nettoyage
rm -f /tmp/test_*.txt /tmp/shell_out.txt

exit $FAILED
