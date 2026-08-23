// 프로그래머스/ 아래를 훑어서 README의 INDEX 블록에 풀이 목록을 만든다.
// 디렉터리 규칙은 백준허브가 만드는 형식을 그대로 따른다: 프로그래머스/<레벨>/<번호>. <제목>/

import { readFileSync, writeFileSync, existsSync, readdirSync, statSync } from "node:fs";
import { join, relative } from "node:path";

const ROOT       = process.cwd();
const README     = join(ROOT, "README.md");
const BASE       = process.env.SOLVED_DIR || "프로그래머스";
const SOLVED_DIR = join(ROOT, BASE);
const LESSON     = (id) => `https://school.programmers.co.kr/learn/courses/30/lessons/${id}`;

// 경로를 마크다운 링크에 넣을 수 있게 인코딩 (한글·공백·괄호 대응)
const enc = (p) => p.split("/").map(encodeURIComponent).join("/");

function collect() {
  const rows = [];
  if (!existsSync(SOLVED_DIR)) return rows;

  for (const lv of readdirSync(SOLVED_DIR, { withFileTypes: true })) {
    if (!lv.isDirectory()) continue;
    const level = /^\d+$/.test(lv.name) ? Number(lv.name) : null;

    for (const dir of readdirSync(join(SOLVED_DIR, lv.name), { withFileTypes: true })) {
      if (!dir.isDirectory()) continue;
      const m = /^(\d+)\.\s*(.+)$/.exec(dir.name);
      if (!m) continue;

      const abs = join(SOLVED_DIR, lv.name, dir.name);
      const files = readdirSync(abs).filter((f) => f.toLowerCase() !== "readme.md");
      const langs = [...new Set(files.map((f) => (f.match(/\.([^.]+)$/) || [, ""])[1].toLowerCase()).filter(Boolean))];

      rows.push({
        id: Number(m[1]),
        title: m[2].trim(),
        level,
        langs,
        path: relative(ROOT, abs).split("\\").join("/"),
        mtime: Math.max(0, ...files.map((f) => statSync(join(abs, f)).mtimeMs)),
      });
    }
  }
  return rows;
}

const LANG_LABEL = { cpp: "C++", cc: "C++", c: "C", py: "Python", java: "Java", js: "JavaScript", kt: "Kotlin", swift: "Swift", go: "Go", cs: "C#", rb: "Ruby", sql: "SQL" };
const label = (l) => LANG_LABEL[l] || l.toUpperCase();

function render(rows) {
  if (rows.length === 0) {
    return "> 아직 올라온 풀이가 없다. 문제를 하나 풀면 여기에 표가 생긴다.";
  }

  const byLevel = new Map();
  for (const r of rows) {
    const k = r.level ?? 0;
    if (!byLevel.has(k)) byLevel.set(k, []);
    byLevel.get(k).push(r);
  }

  const levels = [...byLevel.keys()].sort((a, b) => a - b);
  const out = [];

  // 요약 한 줄
  const chips = levels.map((lv) => `\`Lv.${lv} ${byLevel.get(lv).length}\``).join(" · ");
  out.push(`**총 ${rows.length}문제** — ${chips}`, "");

  for (const lv of levels) {
    const list = byLevel.get(lv).sort((a, b) => b.mtime - a.mtime);
    out.push(
      `<details${lv === levels[0] ? " open" : ""}>`,
      `<summary><b>Level ${lv}</b> · ${list.length}문제</summary>`,
      "",
      "| # | 문제 | 언어 | 풀이 |",
      "|---:|---|---|---|"
    );
    list.forEach((r, i) => {
      const langs = r.langs.map(label).join(", ") || "—";
      out.push(`| ${i + 1} | [${r.title.split("|").join("&#124;")}](${LESSON(r.id)}) | ${langs} | [코드](${enc(r.path)}) |`);
    });
    out.push("", "</details>", "");
  }

  return out.join("\n").trimEnd();
}


const rows = collect();
writeFileSync(README, replaceBlock(readFileSync(README, "utf8"), "INDEX", render(rows)));
console.log(`풀이 목록 갱신 · ${rows.length}문제`);

// README의 <!-- NAME:START --> ~ <!-- NAME:END --> 사이를 통째로 갈아끼운다.
function replaceBlock(md, name, body) {
  const open  = "<!-- " + name + ":START -->";
  const close = "<!-- " + name + ":END -->";
  const i = md.indexOf(open);
  const j = md.indexOf(close, i + open.length);
  if (i < 0 || j < 0) throw new Error("README에 " + name + " 마커가 없습니다.");
  return md.slice(0, i + open.length) + "\n" + body + "\n" + md.slice(j);
}
