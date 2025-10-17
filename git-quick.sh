#!/usr/bin/env bash
set -euo pipefail

# git-quick.sh — مساعد سريع لأوامر Git الشائعة
# استخدامات:
#   ./git-quick.sh setup "YourName" "you@email.com"
#   ./git-quick.sh clone git@github.com:USER/REPO.git [DIR]
#   ./git-quick.sh new-branch BRANCH
#   ./git-quick.sh push "COMMIT MESSAGE" [BRANCH]   # داخل مجلد الريبو
#   ./git-quick.sh status
#   ./git-quick.sh pull
#   ./git-quick.sh remote git@github.com:USER/REPO.git

cmd="${1:-}"

die(){ echo "Error: $*" >&2; exit 1; }
need_repo(){ git rev-parse --is-inside-work-tree >/dev/null 2>&1 || die "ادخلي داخل مجلد الريبو أولاً."; }

case "$cmd" in
  setup)
    name="${2:-}"; email="${3:-}"
    [ -n "$name" ] && [ -n "$email" ] || die "الاستخدام: ./git-quick.sh setup \"YourName\" \"you@email.com\""
    git config --global user.name  "$name"
    git config --global user.email "$email"
    git config --global init.defaultBranch main
    echo "✅ تم ضبط Git باسم: $name، إيميل: $email"
    ;;

  clone)
    url="${2:-}"; dir="${3:-}"
    [ -n "$url" ] || die "الاستخدام: ./git-quick.sh clone <remote_url> [dir]"
    if [ -n "${dir:-}" ]; then
      git clone "$url" "$dir"
      cd "$dir"
    else
      git clone "$url"
      cd "$(basename "$url" .git)"
    fi
    echo "✅ تم الاستنساخ، المجلد الحالي: $(pwd)"
    ;;

  remote)
    need_repo
    url="${2:-}"; [ -n "$url" ] || die "الاستخدام: ./git-quick.sh remote <remote_url>"
    if git remote | grep -q '^origin$'; then
      git remote set-url origin "$url"
    else
      git remote add origin "$url"
    fi
    echo "✅ تم ضبط الريموت: origin → $url"
    ;;

  new-branch)
    need_repo
    br="${2:-}"; [ -n "$br" ] || die "الاستخدام: ./git-quick.sh new-branch <branch>"
    git fetch origin || true
    git checkout -B "$br"
    echo "✅ على الفرع: $br"
    ;;

  push)
    need_repo
    msg="${2:-}"; br="${3:-$(git rev-parse --abbrev-ref HEAD)}"
    [ -n "$msg" ] || die "الاستخدام: ./git-quick.sh push \"COMMIT MESSAGE\" [BRANCH]"
    git add -A
    if ! git diff --cached --quiet; then
      git commit -m "$msg"
    else
      echo "ℹ️ لا يوجد تغييرات للإضافة؛ محاولة دفع الفرع الحالي."
    fi
    git pull --rebase origin "$br" || true
    git push -u origin "$br"
    echo "✅ تم الدفع إلى origin/$br"
    ;;

  status)
    need_repo
    git status -sb
    ;;

  pull)
    need_repo
    br="$(git rev-parse --abbrev-ref HEAD)"
    git pull --rebase origin "$br" || true
    echo "✅ تم السحب (rebase) من origin/$br"
    ;;

  *)
    cat <<USAGE
الاستخدام:
  ./git-quick.sh setup "Shadenm-404" "viuxwl7@gmail.com"
  ./git-quick.sh clone git@github.com:Shadenm-404/holbertonschool-low_level_programming.git
  cd holbertonschool-low_level_programming
  ./git-quick.sh new-branch feature/sll-task0
  # عدّلي الملفات…
  ./git-quick.sh push "singly_linked_lists: add Task 0"
  ./git-quick.sh status
  ./git-quick.sh pull
USAGE
    ;;
esac
