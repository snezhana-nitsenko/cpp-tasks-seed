#!/bin/bash

set -euo pipefail

status=true
tmpdir=$(mktemp -d)
trap 'rm -rf "${tmpdir}"' EXIT

./gauss test01.csv "${tmpdir}/test01_out.csv"
cmp test01_expected.csv "${tmpdir}/test01_out.csv" || status=false

./gauss test02.csv "${tmpdir}/test02_out.csv"
cmp test02_expected.csv "${tmpdir}/test02_out.csv" || status=false

$status
