; ModuleID = 'test/test_mem2reg.ll'
source_filename = "test/test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [9 x i8] c"r0 = %d\0A\00", align 1
@.str.1 = private unnamed_addr constant [9 x i8] c"r1 = %d\0A\00", align 1
@.str.2 = private unnamed_addr constant [9 x i8] c"r2 = %d\0A\00", align 1
@.str.3 = private unnamed_addr constant [9 x i8] c"r3 = %d\0A\00", align 1
@.str.4 = private unnamed_addr constant [9 x i8] c"r4 = %d\0A\00", align 1
@.str.5 = private unnamed_addr constant [9 x i8] c"r5 = %d\0A\00", align 1
@.str.6 = private unnamed_addr constant [9 x i8] c"r6 = %d\0A\00", align 1
@.str.7 = private unnamed_addr constant [9 x i8] c"r8 = %d\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local void @foo(i32 noundef %a, i32 noundef %b, i32 noundef %c) #0 {
entry:
  %0 = shl i32 %a, 4
  %1 = sub i32 %0, %a
  %2 = shl i32 %a, 4
  %3 = sub i32 %2, %a
  %4 = lshr i32 %a, 3
  %add5 = add nsw i32 %b, 1
  %call = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %a)
  %call6 = call i32 (ptr, ...) @printf(ptr noundef @.str.1, i32 noundef %a)
  %call7 = call i32 (ptr, ...) @printf(ptr noundef @.str.2, i32 noundef %b)
  %call8 = call i32 (ptr, ...) @printf(ptr noundef @.str.3, i32 noundef %b)
  %call9 = call i32 (ptr, ...) @printf(ptr noundef @.str.4, i32 noundef %1)
  %call10 = call i32 (ptr, ...) @printf(ptr noundef @.str.5, i32 noundef %3)
  %call11 = call i32 (ptr, ...) @printf(ptr noundef @.str.6, i32 noundef %4)
  %call12 = call i32 (ptr, ...) @printf(ptr noundef @.str.7, i32 noundef %b)
  ret void
}

declare i32 @printf(ptr noundef, ...) #1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 {
entry:
  call void @foo(i32 noundef 24, i32 noundef 5, i32 noundef 2)
  ret i32 0
}

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"clang version 17.0.6"}
